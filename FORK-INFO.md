
This is a fork of Oliver Schröder's mkpwd because I always forget where 
Oliver's website is and the URL for the repository for his highly 
convientent _mkpwd_ utility.

His website URL is http://www.o-schroeder.de/projects/mkpwd
The URL for the repository is git://git.code.sf.net/p/mkpwd/code

How created my fork:

```shell
    git clone git@github.com:rsdoiel/mkpwd
    cd mkpwd
    git remote add upstream git://git.code.sf.net/p/mkpwd/code
    git fetch upstream
    git pull upstream master
    # Merge 1.6 improvements
    wget http://www.o-schroeder.de/download/mkpwd/mkpwd-1.6.tar.gz
    tar zxvf mkpwd-1.6.tar.gz
    cp -v mkpwd-1.6/* ./
    git commit -am "merge 1.6 from tarfile"
    rm -fR mkpwd-1.6 mkpwd-1.6.tar.gz
    git push origin master
```

## Additional changes

Since I am targetting Mac OS X and it nolonger has a **libcrypt**
and provides the `crypt` function via `<unistd.h>`.
I've commented out the section in the `configure.ac`  and 
also changed Makefile.am to exclude the `LIB = -lcrypt`.

I've explicitly add a `#include <ctype.h>` to 
`mkpwd.c` to avoid an error about `tolower()` function definition.

## Installing on Mac OX S (Mojave)

You need XCode 10 installed along with the command line tools

```shell
    xcode-select --install
    xcodebuild -license
```

After that do the following.


```shell
    git clone git@github.com:rsdoiel/mkpwd src/github.com/rsdoiel/mkpwd
    cd src/github.com/rsdoiel/mkpwd
    ./autogen.sh
    ./configure --prefix=$HOME
    make
    make install
```

