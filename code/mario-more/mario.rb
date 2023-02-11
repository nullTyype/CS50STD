name = -> () {
    puts("Height: ")
    gets.chomp.to_i
}

def draw(height)
    spaces = height - 1
    i = 0
    while i < height
        puts ("#{" "}" * spaces + "#{"#"}" * i + "#{"  "}" + "#{"#"}" * i )

        i += 1
        spaces -= 1
    end
end

draw(name.call)