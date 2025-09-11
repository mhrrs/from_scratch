# Things we have learned:

**Compiling the program for execustion:**


**Operator overloading:**
- Where does an issue arise when operator overloading is necessary?: Essentially, when the operator might look to be intuitive to the user, but isn't actually defined within the confines of the way it is being used. Imagine creating a class called Number where you assign it a singular number value and then try to add two of these classes together to get another Number class.
- - This results in a 'Invalid operands to binary expression' error. What this means is that + hasn't been defined to deal with these types of classes.
- for dealing with vectors (or arrays) this requires using a template class as well to generalize the type allowed

NOTE: Technically you can edit one of the operators to do whatever you want... its best to respect the philosophy of each operator for consistency though. the + operator shouldn't return a constant, it should always return a sum and it should always return of similar types...

Exercise: overload an operator to allow you to add characters to create strings..



**Template classes:**
- What is this?:

