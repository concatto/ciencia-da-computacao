using CSV

cd(@__DIR__)

struct Item
	value::Int32
	weight::Int32
end

struct Instance
	total_weight::Int32
	items::Array{Item}
end


mutable struct Solution
	items::Array{Item}
end


function compute_weight(solution::Solution)
	return sum(x::Item -> x.weight, solution.items)
end


function evaluate(solution::Solution)
	return sum(x::Item -> x.value, solution.items)
end

function parse_instance(file_name)
	source = CSV.Source(file_name; header=[])
	first_parts = split(CSV.readline(source), ',')
	second_parts = split(CSV.readline(source), ',')
	third_parts = split(CSV.readline(source), ',')

	max_weight = parse(Int32, first_parts[2])
	values = map(x -> parse(Int32, x), second_parts)
	weights = map(x -> parse(Int32, x), second_parts)

	items = map(vals -> Item(vals[1], vals[2]), zip(values, weights))

	return Instance(max_weight, items)
end

inst = parse_instance("a100.lia")
println(inst)
