<p align="center">
  <a href="https://42lyon.fr/">
    <img src="./assets/final%20grade.png" alt="ft_irc" width=200 height=170>
  </a>

  <h2 align="center">ft_irc</h2>

  <p align="center">
    This project is about creating your own IRC server.
    You will use an actual IRC client to connect to your server and test it.
    Internet is ruled by solid standards protocols that allow connected computers to interact
    with each other
    <br>
    <br>
    <br>
    <a href="./assets/en.subject.pdf">English Subject </a>
    |
    <a href="./assets/fr.subject.pdf"> Sujet en Francais</a>
  </p>
</p>

<p align="center">
  <img src="./assets/Screen%20Shot%202022-09-29%20at%201.58.16%20PM.png" width=600>
</p>

## Table of contents

- [Quick start](#quick-start)
- [Usage](#usage)
- [What's included](#whats-included)
- [Creators](#creators)

## Quick start

ft_irc server with a dedicated bot.

We used <a href="https://weechat.org/"> Weechat</a> as the reference for our client and <a href="https://freenode.net/"> freenode</a> as the reference for the server.

The bot is running like a client and can be connected/disconnected at will. The bot is ominiscient and... has a short fuse.
Dare to use bad words and something may happen to you !
It will only read from the french dictionnary of insults located in ./bot/assets/ but you can still feed the dictionnary by yourself.
It is possible to send private messages to the bot and it will answer accordingly... (randomly to be honest).

As the subject requires it, the server is only running with a password so you will need to set the password accordingly beforehand in weechat to be able to connect to the server.

<img src="./assets/Screen%20Shot%202022-09-29%20at%201.46.37%20PM.png" width=800>

## Usage

to start the server, run 'make' at the root of the directory:
```
./ircserv <port> <password>
```
to start the bot, first you have to run 'make' in the ./bot/ directory:
```
./bot <port>
```

<img src="./assets/Screen%20Shot%202022-09-29%20at%201.44.23%20PM.png" width = 380>

to send a message to the bot with weechat:
```
/msg bot <message>
```
to send a message to the bot with NC:
```
PRIVMSG bot <msg>
```

## What's included

```
ft_irc
├── Makefile
├── README.md
├── assets
│   ├── en.subject.pdf
│   ├── final grade.png
│   └── fr.subject.pdf
├── bot
│   ├── Makefile
│   ├── assets
│   │   ├── dict_insult_engl.txt
│   │   └── dict_insult_fr.txt
│   ├── bot
│   ├── includes
│   │   ├── BotCommons.hpp
│   │   └── BotExceptions.hpp
│   └── srcs
│       ├── Bot
│       │   ├── Bot.cpp
│       │   └── Bot.hpp
│       ├── Client
│       │   ├── BotClient.cpp
│       │   ├── BotClient.hpp
│       │   └── privateBotClient.cpp
│       └── main.cpp
├── includes
│   ├── commons.hpp
│   ├── exceptions.hpp
│   └── numeric_replies.hpp
├── setups_files_auth.txt
├── srcs
│   ├── Channel
│   │   ├── Channel.cpp
│   │   └── Channel.hpp
│   ├── Client
│   │   ├── Client.cpp
│   │   └── Client.hpp
│   ├── ExecutionManager
│   │   ├── ExecutionManager.cpp
│   │   ├── ExecutionManager.hpp
│   │   └── commands
│   │       ├── bot.cpp
│   │       ├── cap.cpp
│   │       ├── invite.cpp
│   │       ├── join.cpp
│   │       ├── kick.cpp
│   │       ├── kill.cpp
│   │       ├── mode.cpp
│   │       ├── nick.cpp
│   │       ├── notice.cpp
│   │       ├── part.cpp
│   │       ├── pass.cpp
│   │       ├── ping.cpp
│   │       ├── privmsg.cpp
│   │       ├── quit.cpp
│   │       ├── topic.cpp
│   │       └── user.cpp
│   ├── Server
│   │   ├── Server.cpp
│   │   ├── Server.hpp
│   │   └── privateServer.cpp
│   └── main.cpp
└── tests.txt
```

## Creators

**abonnel**

- <https://github.com/anyaa6>

**mballet**

- <https://github.com/mbllt>

**llecoq**

- <https://github.com/llecoq>
