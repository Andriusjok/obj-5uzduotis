# OOP


## Last assignment

[Text source](https://www.washingtonpost.com/technology/2019/06/10/your-face-is-now-your-boarding-pass-thats-problem/?utm_term=.719a04479de6)

containers utilized - multimap for repetitive words and vector for urls.

# 1 - 2 parts:

Because the assignment didn't require us to have UTF-8 support, I didn't do it. I used a multimap {Word, Linenr} to create the crossrefence and gather the words. Since there's no UTF-8 I just checked if the characters are characters/numbers or not.

# part 3

I used a regex that I found online to check if a string is a valid url or not.

# Makefile: make makes exe file and clean deletes it.
```
CC=g++
main:
	$(CC) -o main main.cpp
clean:
	rm *.o *.exe
```
