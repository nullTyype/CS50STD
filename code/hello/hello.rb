name = -> () {
    puts("Name: ")
    return gets.chomp
} 
STDERR.puts("hello #{name.call}")