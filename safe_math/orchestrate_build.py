import os
import shutil
import errno
from pathlib import Path
from build import ProjectBuilder
from build.env import DefaultIsolatedEnv

components = ["core", "exp"]
config_dir = Path("config")
project_root = Path("./")

def find_pyprojects(comps):
    if not config_dir.exists():
        raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), config_dir)
    configs_list = []
    for component in comps:
        config_path = config_dir / f"{component}.toml"
        if not config_path.exists():
            raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), config_path)
        configs_list.append(config_path)
    return configs_list

configs_list = find_pyprojects(components)
# one env for all builds: a fresh env per build changes scikit-build-core's
# install path, which makes it wipe the CMake cache in SKBUILD_BUILD_DIR
with DefaultIsolatedEnv() as env:
    for config_path in configs_list:
        current_pyproject = project_root / "pyproject.toml"
        shutil.copy(config_path, current_pyproject)
        try:
            builder = ProjectBuilder.from_isolated_env(env, ".")
            env.install(builder.build_system_requires)
            env.install(builder.get_requires_for_build("wheel"))
            path = builder.build("wheel", "dist")
        finally:
            current_pyproject.unlink()
