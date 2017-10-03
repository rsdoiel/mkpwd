
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
    tar xvf mkpwd-1.6.tar.gz
    cp -v mkpwd-1.6/* ./
    git commit -am "merge 1.6 from tarfile"
```

