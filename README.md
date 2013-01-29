OneTimer
========

Command-line C programs for doing encryption and decryption using the [one-time pad][otp] (OTP).

  [otp]: http://en.wikipedia.org/wiki/One-time_pad

It consists of three programs:

  1. `encrypt` takes a key and a plaintext and returns a ciphertext:

    > ./encrypt -k f00bd00b -p "Derp"  
    b46ea27b

  2. `decrypt` takes a key and a ciphertext and returns a plaintext:

    > ./decrypt -k f00bd00b -c b46ea27b  
    Derp

  3. `crack` takes a plaintext and a ciphertext and returns a key:

    > ./crack -p "Derp" -c b46ea27b  
    f00bd00b

* * *

Though the one-time pad has [perfect secrecy][pfs], please don't use this for anything serious.

  [pfs]: http://en.wikipedia.org/wiki/One-time_pad#Perfect_secrecy
