struct Item
	value::Int32
	weight::Int32
end

struct Instance
	total_weight::Int32
	items::Array{Item}
end

mutable struct Solution
	items::Array{Int32}
end

function sum_solution(solution::Solution, instance::Instance, func::Function)
	tuples = collect(enumerate(solution.items))
	filtered = filter(x -> x[2] == 1, tuples)

	if length(filtered) == 0
		return 0
	end

	items = map(x -> instance.items[x[1]], filtered)

	return sum(func, items)
end

function compute_weight(solution::Solution, instance::Instance)
	return sum_solution(solution, instance, x -> x.weight)
end

function evaluate(solution::Solution, instance::Instance)
	weight = compute_weight(solution, instance)

	if weight <= instance.total_weight
		return sum_solution(solution, instance, x -> x.value)
	else
		return instance.total_weight - weight
	end
end


function delta_weight(solution::Solution, instance::Instance, index::Int, new_value::Int)
	weight = instance.items[index].weight

	return new_value == 0 ? -weight : weight
end

function delta_quality(solution::Solution, instance::Instance, index::Int, new_value::Int, previous_weight::Int)
	new_weight = previous_weight + delta_weight(solution, instance, index, new_value)

	if new_weight <= instance.total_weight
		value = instance.items[index].value

		return new_value == 0 ? -value : value
	else
		return instance.total_weight - new_weight
	end
end
