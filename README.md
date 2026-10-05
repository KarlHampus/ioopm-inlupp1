### Getting started
# Compiling
Run "make".

# Running tests
Run "make test".

# Running the freq_count program
Run "make freq_count".

### Design decisions
# Error handling
Erros are handled by asserts / crashing if the inputs are invalid, otherwise returing a boolean if the function was successful or not.

# Hash table ownership
The hash table does not by default take ownership of the keys and values, however the user has the option of adding an on entry destroy function that will be ran at the beginning of the destruction of each entry. This essentially lets the user decide if the hash table should own the data or not.

# Linked list ownership
The linked list does not own the inserted data, so strings or void pointers would need to be freed on their own.
