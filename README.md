
![Logo](https://i.imgur.com/Zg37VpH.png)
# SpecSeek. All in One Specification Tool

A soloution to finding everything there is to know about a computers specifications. all in one elegant location. **a great way to share your device specifications support and features**. not sure if your PC supports some functionality? Spec Peek will relay that to you.

## Contributing
I would love to have anyone contribute to fixing bugs or extending feature support, please feel free to make a pull request, or even fork it! *with the licence in mind*.

**When contributing please try follow the naming standard used already, and do not add repeat functionality. please keep a simple codebase as a priority.**
## Build & Run from Source

to build the ELF executables use the following command
``` bash
make
```
however to create the Windows Executables use the following command
``` bash
make windows
```

You can add specseek to MinOS from source by cloning MinOS
```
git clone https://github.com/Dcraftbg/MinOS.git
```

and then downloading the [MinOS Specseek Installer (for source)](https://github.com/Mellurboo/SpecSeek/blob/620c6199ec021c5a2d4f976964307b47c0dabd6c/install_specseek.sh)

place the script at the root of MinOS and run it. and thats it, you are done!

## Documentation
Documentation is held within the github wiki [here](https://github.com/Mellurboo/SpecSeek/wiki). I will try to keep up with it but if anything is missing feel free to raise an issue about it. However the code is commented with detailed comments so I suspect you will be able to fill in the blanks.
## Minimum Requirements
Currently your CPU must be at least 32-bit and have the CPUID instruction.

- AMD-K5 processor models 1, 2, 3
- Intel SL-Enhanced 486


## Appendix
I am creating this project as a soloution to people not knowing their PC specifications, It will be a great way for novice users to find out everything they need to know compiled into a file (or other medium) and sent off to a technition, friend, buyer or that one family friend who claims to be able to fix your device.

Cross-Platform support is a high priority not only making sure SpecSeek can be ran on most operating systems but also making sure it works on many archetectures on many different configurations hardware and software alike.

also sorry for the inconsistancy of how I comment, sometimes I feel /// is appropriate usually for the top of functions, sometimes I use // for comments in the function, if im writing a block of text ill use /* */ but sometimes I might use them interchangably. Feel free to change them.