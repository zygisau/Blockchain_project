# Blockchain project

![version][version-badge]  

This is a simple bitcoin clone.

Currency: (っ◔◡◔)っ ♥ NNT ♥ (No Name Yet)

## What does it do?

This implementation provides a quick example how a basic blockchain could work. There are several tasks this can do at the moment:
- Generate specific number of users
- Generate transactions between those users
- Validates them from evil third parties that might change transaction details while it transfers to the transaction pool
- Validates if sender has enough funds to proceed
- Mine genesis block
- Mine other blocks till there is no transaction in the pool
- Imitates P2P network

> Notes: There is a possibility to use one of the two provided hash algorithms. One of them is created by me - [ŽA-256]( https://github.com/zygisau/ZA-256 ). The other one is highly popular C++ implementation of [SHA-256](http://www.zedwood.com/article/cpp-sha256-function) by zedwood.com

## Silly P2P network imitation

Implementation is pretty simple

- Program creates 5 blocks.
- Takes a random block and tries to mine it.
- If succeeded:
	- Deletes unused blocks
	- Moves unused transactions to the pool
	- Goes to the first point again
- If it fails to mine the block for a certain time of attempts, a new block is chosen.
- If all blocks were tried and failed to mine, the count of attempts is increased by 20 attempts.
- Algorithm continues to run till all transactions are distributed through blocks.

## Installation

In order to run a program, follow these steps
- `git clone git@github.com:zygisau/Blockchain_project.git` <-- if You are using SSH

- `git clone https://github.com/zygisau/Blockchain_project.git` <-- else  

- `cd Blockchain_project` 

- Run CMakeLists.txt file with CMAKE.



## Changelog

### [v0.2.1](https://github.com/zygisau/Blockchain_project/releases/tag/0.2.1) - (2019-10-27)  

**Changed**
 - Changed P2P network imitation strategy to avoid loosing transactions
 - Updated README file


### [v0.2](https://github.com/zygisau/Blockchain_project/releases/tag/0.2) - (2019-10-25)  

**Added**  
 - Transactions validation
 - P2P network imitation

**Changed**
 - Updated README file


### [v0.1](https://github.com/zygisau/Blockchain_project/releases/tag/0.1) - (2019-10-18)  

**Added**  

 - Simple blockchain structure
 - Blockchain generation and mining scenario
 - Created README file

[version-badge]: https://img.shields.io/badge/version-0.2.1-purple.svg
