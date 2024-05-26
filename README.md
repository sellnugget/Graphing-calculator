This is a graphing calculator build in C++ using sfml for graphics. it can take a function in for example x^2 and then render
it to the screen. more features to come soon!!!!!.



i use a compiled model so i can have more control and manipulation over the equations before rendering. 

for example i first parse the equations into a AST(abstract syntax tree). then i can do things like rearrange the equation etc.
maybe the user wants to rendering a equation that would otherwise be complex to do so this allows them to.

also so that x^2 can be converted into the shader code pow(x, 2) automatically and easily. 
