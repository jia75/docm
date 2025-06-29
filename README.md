# Docm

![Static Badge](https://img.shields.io/badge/License-GPL_2-red)

Docm is a graph-based organization and linking layer. You can use it to create systems where files (documents) are connected with eachother through named links. It is made available under the terms of the GNU Public License (available in the file called `LICENSE`).

## Usage

The form of this program is a collection of simple, independent, and portable (POSIX compliant) shell scripts that collectively allow a full suite of features. Most of the time, the user doesn't directly call these shell scripts, but rather uses the `docm` command that acts as a dispatcher to these shell scripts, depending on its arguments.

In order for any of these files to be accessible as regular commands, their location has to be contained in `$PATH`. This can be done by including some random directory in `$PATH` (bad idea: it will fill `$PATH` up with junk), or, alternatively, by moving these files to a location that already is in `$PATH` (something like `/bin/`). You can also temporarily add some directory to `$PATH`, if you just want to test Docm out.

To understand more details regarding the function of Docm, it is recommended to read the documentation which you can find either in the `docs/` directory, either in executing the `docm help` command.
