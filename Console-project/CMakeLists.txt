cmake_minimum_required(VERSION 3.17)

project(Hangman)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HangmanSource 
	"Source/*.hpp"
	"Source/*.cpp"
)

add_executable(Hangman ${HangmanSource})
