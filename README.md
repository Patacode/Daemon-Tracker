# Daemons & Systemd

This repo contains a project around Daemons & Systemd.

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#description">Description</a></li>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#build-and-run">Build and run</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contribution">Contribution</a></li>
  </ol>
</details>

## About The Project

The project consist of a **daemon** tracking all the user activity and backing it up in a log file.

The purpose of this project is to give a concrete practical example on how daemons work in Linux and how
Systemd helps us in the lifecycle management of daemons and their instantiation.

A prior knowledge of Linux systems is assumed, especially around how **signals** work, and how processes are 
handled by the system.

Emphasis is placed on daemons, meaning all the security part, such as dealing with file permissions and related
stuff, is not at the heart of this project.

### Description

Here is how the project is organized:

- There is a first daemon (the **daemon worker/broker**) tracking the `/log` directory for file creation. This daemon will
be a new-style daemon monitored by systemd and will have a boot-based activation during the `multi-user` target phase.

- By convention, the name of the files created in the `/log` directory will denote the absolute path name to a file/directory
we want to track (in dot notation).

- When a file is created in this directory, the daemon worker/broker will create a forking daemon (a **daemon tracker**) able to track user 
activity on the file/directory denoted by the name of this newly created file. 

- The daemon tracker will start watching the file/directory for changes using **inotify** and will write those changes
in the previously created file.

- Each time a file is created in the `/log` directory, denoting a new *watch* location, the factory daemon will start creating
new forking daemons to track these new locations. If the created log file denotes an existing *watch* location, the daemon worker/broker
will synchronized the event queue of the underlying daemons (This will be the case if the **inode** corresponding to
*watch* location is already bound to the inotify instance).

- The daemon worker/broker will stop its execution after having received the **SIGTERM** signal (typically received to clean up
resources after itself). And all the sub forking daemons it has created will be destroyed as well.

### Built with

* [C](https://en.cppreference.com/w/c)
* [inotify](https://man7.org/linux/man-pages/man7/inotify.7.html)
* [systemd](https://systemd.io/)
* [journald](https://www.freedesktop.org/software/systemd/man/systemd-journald.service.html)
* [Make](https://www.gnu.org/software/make/manual/make.html)
* [BashScript](https://www.gnu.org/software/bash/)

## Getting started

To get the application's project up and running locally follow the steps below.

### Prerequisites

You will essentially need *gcc* and *make* to compile and run the project. Systemd is also required as init system
and/or only as, service manager.

Under most Linux distros, all the required tools come directly with the installation. Install them if needed.

Nowadays, systemd is the most popular init system and you propably already have it too. Change your distro or install it 
if needed.

Finally, a bash-like terminal is required to run the provided scripts.

### Build and run

Once all the required tools are installed, setup and ready to be used, you will just have to run the `setup` script, 
found at the project's root (sudo rights are needed):

```bash
./setup start enable
```

This script will essentially compile the project and setup the underlying service so that systemd can use it, start it and 
enable it.

The daemon worker/broker and all its daemon trackers can be stopped and killed using the following command:

```bash
sudo systemctl stop dtrack
```

Afterwards, the `save` script (also located at the project's root) can be used to save the daemon trackers logs under
the `backup/` directory of the project:

```bash
./save
```

## Usage

Here is a simple demo showing you how the project work:

![demoApp](/res/demo-daemonTracker.gif)

## Contribution

This little project has been made by:

* Maximilien Ballesteros

