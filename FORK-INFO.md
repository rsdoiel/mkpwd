
This is a fork of Oliver Schröder's mkpwd because I always forget where Oliver's website is
and can't remember the URL for the repository for his highly convientent _mkpwd_ utility.

His website URL is http://www.o-schroeder.de/projects/mkpwd
The URL for the repository is git://git.code.sf.net/p/mkpwd/code

I setup my fork as follows

```shell
    git clone git@github.com:rsdoiel/mkpwd
    git remote add upstream git://git.code.sf.net/p/mkpwd/code
    git fetch upstream
    git pull upstream master
    wget http://www.o-schroeder.de/download/mkpwd/mkpwd-1.6.tar.gz
    tar zxvf mkpwd-1.6.tar.gz
    cp -v mkpwd-1.6/* ./
    git commit -am "merge 1.6 from tarfile"
    rm -fR mkpwd-1.6 mkpwd-1.6.tar.gz
    git push origin master
```

After fixing the version number in mkpwd.c to reflect the version in the
comments commited and pushed to my master.

Installation process is now

```shell
    git clone git@github.com:rsdoiel/mkpwd src/github.com/rsdoiel/mkpwd
    cd src/github.com/rsdoiel/mkpwd
    ./autogen.sh
    ./configure --prefix=$HOME
    make
    make install
```

