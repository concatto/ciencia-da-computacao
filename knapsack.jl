using CSV

struct Item
	weight::Int32
	value::Int32
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



test = Solution([
	Item(1, 1),
	Item(2, 4),
	Item(4, 2),
	Item(3, 1)
])


source = CSV.Source("a100.lia"; header=[])
println(CSV.readline(source))
println(CSV.readline(source))
println(CSV.readline(source))
