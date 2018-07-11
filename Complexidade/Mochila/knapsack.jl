using CSV
using DataFrames

cd(@__DIR__)
include("knapsack_defs.jl")

function parse_instance(file_name)
	source = CSV.Source(file_name; header=[])
	first_parts = split(CSV.readline(source), ',')
	second_parts = split(CSV.readline(source), ',')
	third_parts = split(CSV.readline(source), ',')

	max_weight = parse(Int32, first_parts[2])
	values = map(x -> parse(Int32, x), second_parts)
	weights = map(x -> parse(Int32, x), third_parts)

	items = map(vals -> Item(vals[1], vals[2]), zip(values, weights))

	return Instance(max_weight, items)
end

# ==========================================


function create_solution(instance::Instance)
	solution = Solution(zeros(length(instance.items)))
	indices = collect(1:length(instance.items))
	shuffle!(indices)

	weight = 0
	for index ∈ indices
		item = instance.items[index]

		if weight + item.weight <= instance.total_weight
			solution.items[index] = 1
			weight += item.weight
		else
			break
		end
	end

	return solution
end

function make_movement(solution::Solution, instance::Instance, from::Int, to::Int)
	best_quality = evaluate(solution, instance)
	original_quality = best_quality
	original_weight = compute_weight(solution, instance)
	best_index = 0

	for (index, value) ∈ shuffle(collect(enumerate(solution.items)))
		# if index % 100 == 0
		# 	println("Checking neighbor n. $index; last improvement: $last_improvement")
		# end

		if value == from
			#neighbor = Solution(copy(solution.items))
			#neighbor.items[index] = to
			change = Δquality(solution, instance, index, to, original_weight)
			#neighbor_quality = evaluate(neighbor, instance)
			# println("Changed an item which cost ", instance.items[index].weight)
			# println("Improvement: ", neighbor_quality - original_quality)

			if change > 0
				best_quality = original_quality + change
				best_index = index

				break # first improvement
			end
		end
	end

	if best_index == 0
		best = solution
	else
		best = Solution(copy(solution.items))
		best.items[best_index] = to
	end

	return best, best_quality
end

function try_remove(solution::Solution, instance::Instance)
	return make_movement(solution, instance, 1, 0)
end

function try_insert(solution::Solution, instance::Instance)
	return make_movement(solution, instance, 0, 1)
end

function try_exchange(solution::Solution, instance::Instance)
	best = solution
	best_quality = evaluate(solution, instance)

	for (index, value) ∈ shuffle(collect(enumerate(solution.items)))
		if value == 1
			# Let's remove this item
			neighbor = Solution(copy(solution.items))
			neighbor.items[index] = 0

			# Now let's try adding one
			best_neighbor, best_neighbor_quality = try_insert(neighbor, instance)

			if best_neighbor_quality > best_quality
				improvement = best_neighbor_quality - best_quality
				#println("Q: $best_neighbor_quality; improved by $improvement")
				best = best_neighbor
				best_quality = best_neighbor_quality

				break
			end
		end
	end

	return best, best_quality
end



function local_search(initial::Solution, instance::Instance)
	best = initial
	best_quality = evaluate(initial, instance)

	while true
		new_best, new_best_quality = try_insert(best, instance)

		if new_best_quality > best_quality
			best = new_best
		else
			break
		end
	end

	while true
		new_best, new_best_quality = try_exchange(best, instance)

		if new_best_quality > best_quality
			best = new_best
			best_quality = new_best_quality
		else
			break
		end
	end

	return best
end


function run_experiments(replications)
	files = filter(x -> endswith(x, "a10000.lia"), readdir("."))

	experiments = DataFrame(
		file=AbstractString[],
		replication=Int[],
		elapsed_time=Float64[],
		quality=Int64[],
		items=Int32[],
	)

	for file_name ∈ files
		inst = parse_instance(file_name)
		println(file_name)
		for replication ∈ 1:replications
			println(replication)
			tic()
			initial = create_solution(inst)

			best = local_search(initial, inst)
			time = toq()
			quality = evaluate(best, inst)
			println(best)
			println(compute_weight(best, inst))

			row = [file_name, replication, time, quality, length(inst.items)]
			println(row)
			push!(experiments, row)
		end
	end

	#CSV.write("experiments2.csv", experiments)
end


#sol = create_solution(inst)

#best = local_search(sol, inst, true)

#println(best)
#println(evaluate(best, inst))
#println(compute_weight(best, inst))

run_experiments(1)
#run_experiments(30)
