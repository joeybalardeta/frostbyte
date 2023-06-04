# Frostbyte
A custom chess engine, written in C. This was inspired by my school project to build a chess program (that program is publicly available under my r_chess repository). I wanted to improve upon it by optimizing memory usage and making a more 'intelligent' AI to play against the user.

## Goals
 - Make an optimized chess engine
 - Keep the code simple
 - Make an 'AI' that is capable of beating players up to 2000 rating
 - No API's for AI move making

## Current Features
- Player vs Player
- Player vs Computer
- Computer vs Computer
- FEN string parsing to set up custom boards (only available for move simulation right now)

## Future Planned Features
 - Smarter AI (random moves are funny, but they don't win games)
 - Computer vs Computer | Machine Learning Mode


## Project Info
 - Developed in WSL Ubuntu + MacOS Ventura
 - Compiled with gcc
 - Compatibile with any OS (gcc and make required)


## Currently Working On
 - Rewriting the Piece struct
   - Piece struct -> single unsigned char
   - Piece type and color encoded (read through bit masks)
   - Since the unsigned char cannot hold a moveCount attribute, I will be adding more to the Game struct to account for castling and En Passant (castling rights variables + En Passant target square)
