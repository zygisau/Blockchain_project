# Blockchain project

![version][version-badge]  

This is a simple bitcoin clone.

Currency: (っ◔◡◔)っ ♥ NNT ♥ (No Name Yet)

## What does it do?

This implementation provides a quick example how a basic blockchain could work. There are several tasks this can do at the moment:
- Generate specific number of users
- Generate transactions between those users
- Mine genesis block
- Mine other blocks till there is no transaction in the pool

> Notes: There is a possibility to use one of the two provided hash algorithms. One of them is created by me - [ŽA-256]( https://github.com/zygisau/ZA-256 ). The other one is highly popular C++ implementation of [SHA-256](http://www.zedwood.com/article/cpp-sha256-function) by zedwood.com

## Installation

In order to run a program, follow these steps
- `git clone git@github.com:zygisau/Blockchain_project.git` <-- if You are using SSH

- `git clone https://github.com/zygisau/Blockchain_project.git` <-- else  

- `cd Blockchain_project` 

- Run CMakeLists.txt file with CMAKE.




## Changelog

### [v0.1](https://github.com/zygisau/Blockchain_project/releases/tag/0.1) - (2019-10-18)  

**Added**  

 - Simple blockchain structure
 - Blockchain generation and mining scenario
 - Created README file

[version-badge]: https://img.shields.io/badge/version-0.1.1-purple.svg
