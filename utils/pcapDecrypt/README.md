# pcapDecrypter



###Compile on Windows
To compile the pcap decrypter on Windows, run the following (MinGW):

`g++ pcapDecrypt.cpp base64.cpp blowfish.cpp -m32 -lws2_32 -lwpcap -o "pcapDecrypt.exe"`

Note: You need to have the developer's pack of winpcap to compile this: [Winpcap Devel](http://www.winpcap.org/devel.htm)

Unzip the .zip file and put the files in Lib in
`C:\MinGW\lib`
and put the files in Include in
`C:\MinGW\include`