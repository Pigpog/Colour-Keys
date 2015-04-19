Colour-Keys
=========

Transforms a hexadecimal key into a colourful encoded image, and allows for reversal of the process to obtain the original key. This allows for a simple means of public key exchange, much like a .pub file, but more stylish (in my opinion).

How it works
=========

make_keyimg() takes a string as input, such as: "2c349b1cbe1fe87546fcb28f35ee4b1674a0fbcaaea861da7c63ef224008b1e258354ffed963"

and produces an image like this: 

[![Screenshot](http://i.imgur.com/2sOXSnK.jpg)](http://i.imgur.com/2sOXSnK.jpg)

extract_keyimg() does the reverse; it reads an image produced by make_keyimg() and returns a string containing the encoded public key.

Notes
=========

* The template image could be virtually anything; I wrote it with the ProjectTox messenger in mind, hence the logo and file extensions
* This is only a proof of concept thrown together in a couple days, and as such may contain bugs.
* One known bug/flaw is that a key where a pixel is made up of the background colour (e.g. #ffffff for a white background) will not be extracted correctly. Despite being over a 1 in a million chance, a special case must be made with key generation to ensure integrity.
* The unit test can be used by running the command make
