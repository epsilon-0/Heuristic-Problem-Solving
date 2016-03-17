#!/bin/sh
rm -rf compile
rm org.sat4j.core.jar
mkdir compile
cd compile
unzip ../sat4j-core-v20110206.zip
rm org.sat4j.core.jar
jar xf org.sat4j.core-src.jar
cp ../build.xml .
ant
ln -s compile/dist/CUSTOM/org.sat4j.core.jar ..