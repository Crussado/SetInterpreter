# SetInterpreter
An interactive set interpreter. Made in C using hash table and interval trees.
# Compile and Execute
- make
- Execute 'programa'.
# Commands
Respect the spaces.
Can define set with:
- By comprehension: `alias = {x_{0},x_{1},...,x_{n}}`
- By extension: `alias = {x : k_{0} <= x <= k_{1}}`
Can operate sets with:
- Union: `alias_{1} = alias_{2} | alias_{3}`
- Intersection: `alias_{1} = alias_{2} & alias_{3}`
- Subtraction: `alias_{1} = alias_{2} - alias_{3}`
- Complement: `alias_{1} = ~alias_{2}`

Print sets with: `imprimir alias`

Exit: `salir`
