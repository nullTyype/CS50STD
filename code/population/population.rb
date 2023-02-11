startsize = ARGV[0].to_f
endsize = ARGV[1].to_f

def timeElapsed(startsize, endsize)
    years = 0
    population = startsize

    while population + population/12 < endsize
        population += population/12
        years += 1
        puts "Year: #{years}, Population: #{population}"
    end

    puts "Years: #{years + population/endsize}"
end

if (startsize.is_a? Float) && (endsize.is_a? Float) && (startsize > 2)
    timeElapsed(startsize, endsize)
else
    STDERR.puts <<-eof
    INVALID ARGUMENT:
        Start size must be greater than 2;
    eof
end