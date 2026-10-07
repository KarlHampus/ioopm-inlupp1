### Getting started
# Compiling
Run "make".

# Running tests
Run "make test".

# Running the freq_count program
Compile with "make freq_count".
To run the program with a custom file, run "make run_freq_count FILE=" followed by the file name in quotes.

### Design decisions
# Error handling
Erros are handled by asserts / crashing if the inputs are invalid, otherwise returing a boolean if the function was successful or not.

# Hash table ownership
The hash table does not by default take ownership of the keys and values, however the user has the option of adding an on entry destroy function that will be ran at the beginning of the destruction of each entry. This essentially lets the user decide if the hash table should own the data or not.

# Linked list ownership
The linked list does not own the inserted data, so strings or void pointers would need to be freed on their own.

### Initial profiling results
Everything is based on the results from gprof. Because the 16k words file took a very short time, we also added the bible in swedish because it contains a lot of words and takes longer.

# Top 3 functions for each test file
small.txt:
Calls   % time   Self s   Name
60      0.00     0.00     cmp_freq_words
56      0.00     0.00     ioopm_hash_table_iterator_at_end
54      0.00     0.00     find_pointer_to_entry

1k-long-words.txt:
Calls   % time   Self s   Name
3564    0.00     0.00     ioopm_string_equal
2000    0.00     0.00     find_pointer_to_entry
2000    0.00     0.00     ioopm_string_hash

10k-words.txt:
Calls    % time   Self s   Name
115860   0.00     0.00     ioopm_string_equal
20000    0.00     0.00     find_pointer_to_entry
20000    0.00     0.00     ioopm_string_hash

16k-words.txt:
Calls   % time   Self s   Name
33984   100.00   0.01     find_pointer_to_entry
2494074 0.00     0.00     ioopm_string_equal
35934   0.00     0.00     cmp_freq_words

bibeln.txt:
Calls       % time   Self s   Name
1477808     62.65    1.04     find_pointer_to_entry
438680812   28.92    0.48     ioopm_string_equal
(none)      3.61     0.06     _init

# Top 3 functions discussion
The top three functions varies a bit, find_pointer_to_entry is the only one consistently in the top three, and ioopm_string_equal is in the top three in all but the first. The functions are all our own funcitons except for _init.

When the files get longer with more words, there will be more entries and the program will therefore spend more time comparing entries and finding an entry. Since the hash table, at the moment, is limited to 17 buckets, each bucket will contain a lot of entries that are needed to be stepped through and compared to the key we are looking for. This is the reason to why find_pointer_to_entry and ioopm_string_equal are used a lot.

# Our expectations
These results are not a surprise since we knew the low bucket count would cause the program to do a lot of comparing, and naturally find_pointer_to_entry is used by most hash table functions.

# Possible improvements
We could significantly improve the program by increasing the number of buckets, and possibly finding a way to make find_pointer_to_entry more efficient. Another way to improve the program might be to create a more efficient compare function that only checks for difference and terminates as soon as it finds it.

# Time results (for future comparison)
Command being timed: "./freq_count bibeln.txt"
User time (seconds): 0.62
System time (seconds): 0.37
Percent of CPU this job got: 98%
Elapsed (wall clock) time (h:mm:ss or m:ss): 0:01.01
Average shared text size (kbytes): 0
Average unshared data size (kbytes): 0
Average stack size (kbytes): 0
Average total size (kbytes): 0
Maximum resident set size (kbytes): 6656
Average resident set size (kbytes): 0
Major (requiring I/O) page faults: 3
Minor (reclaiming a frame) page faults: 1358
Voluntary context switches: 13
Involuntary context switches: 5
Swaps: 0
File system inputs: 10112
File system outputs: 64
Socket messages sent: 0
Socket messages received: 0
Signals delivered: 0
Page size (bytes): 4096
Exit status: 0
