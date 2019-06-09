import os
import re
import subprocess
from typing import Tuple,Dict,List, Any
import platform
from pathlib2 import Path

def run_command(cmds:List[str])->None:
    subprocess.run(cmds)
    return None

def compile()->None:
    os.chdir(Path(__file__).parent)
    cmk_generator_command: List[str]= []
    cmk_build_command:List[str] = []

    if str(platform.system()).upper().strip() in set(["WINDOWS"]):
        cmk_generator_command = ['cmake', '-G', 'Visual Studio 16 2019','-A','x64' ,'.']
        cmk_build_command =['cmake','--build', '.', '--config', 'Release']
    elif str(platform.system()).upper().strip() in set(["DARWIN"]):
        cmk_generator_command = ['cmake', '.']
        cmk_build_command = ['cmake', '--build', '.', '--config', 'Release']
    else:
        cmk_generator_command = ['cmake', '.']
        cmk_build_command = ['cmake', '--build', '.', '--config', 'Release']
    run_command(cmk_generator_command)
    run_command(cmk_build_command)
    return None

if __name__=="__main__":
    compile()
