# Kansai Visual Novel Engine
The Viktor Chondria team's abstract, cross-platform Visual Novel Engine.

## Script Format
The Kansai engine uses a custom script format designed as:
```
DEFINE character name can continue until EOL
default  ../img/character/default.png
surprise ../img/character/surprise.png
ENDDEFINE

ENTRY scene_name # first scene. This can only be defined once and will be ignored later on.

SCENE scene_name # no spaces; the result of the choice at the end is stored in $scene_name
B ../background/b1.png
S character WITH default ON left # show character with sprite as defined above
D character : dialogue continues until EOL but can be broken up with \n literal.
D character : this continues until the end of the scene
J jmp_to # jump unconditional
JE var_name value scene_2 # jump if equal
JE var_name value $var_2 # $ prefix is for variables in comparisons
C choices jmp_to ; choice2 jmp_to_different
ENDSCENE # scenes cannot be nested

SCENE jmp_to # new scene
B ../background/b1.png
S character WITH surprise ON left
S character with default ON RIGHT
D character : we're now in a new scene
ENDSCENE # when no other scene is reached, the game ends.
```
As long as all the files are loaded, it does not matter what is in what file and in what order.