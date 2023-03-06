# Implement the general search algorithm. Experiment with Best-First and A* search on the 8-puzzle

import sys
import time
import heapq
import math
import copy

# Global variables
# The goal state
goal = '1238B4765'

def h(state):
	# The heuristic function
	# state: the state
	# return: the heuristic value

	# Initialize the heuristic value
	h = 0

	# Calculate the heuristic value
	for i in range(len(state)):
		if state[i] != goal[i]:
			h += 1
	return h

def GetChildren(state):
	# Get the children of the state
	# state: the state
	# return: the children of the state

	# Initialize the children list
	children = []

	# Get the index of the blank tile
	index = state.index('B')

	# Move the blank tile up
	if index > 2:
		child = list(state)
		child[index] = child[index - 3]
		child[index - 3] = 'B'
		children.append(''.join(child))

	# Move the blank tile down
	if index < 6:
		child = list(state)
		child[index] = child[index + 3]
		child[index + 3] = 'B'
		children.append(''.join(child))

	# Move the blank tile left
	if index % 3 != 0:
		child = list(state)
		child[index] = child[index - 1]
		child[index - 1] = 'B'
		children.append(''.join(child))

	# Move the blank tile right
	if index % 3 != 2:
		child = list(state)
		child[index] = child[index + 1]
		child[index + 1] = 'B'
		children.append(''.join(child))

	return children


def BestFirstSearch(state):
	# Implement the best-first search algorithm
	# state: the initial state
	# h: the heuristic function
	# return: the path from the initial state to the goal state

	# Initialize the open list
	open = []
	# Initialize the closed list
	closed = []
	# Initialize the path
	path = []

	path.append(state)

	# Add the initial state to the open list
	heapq.heappush(open, (h(state), state))

	while len(open) > 0:
		# Get the state with the lowest heuristic value
		(f, state) = heapq.heappop(open)
		# Add the state to the closed list
		closed.append(state)

		# If the state is the goal state, return the path
		if state == goal:
			return path

		# Get the children of the state
		children = GetChildren(state)
		for child in children:
			# If the child is not in the closed list, add it to the open list
			if child not in closed:
					heapq.heappush(open, (h(child), child))
					# Add the child to the path
					path.append(child)

	# Return None if the goal state is not found
	return None


def AStarSearch(state):
	# Implement the A* search algorithm
	# state: the initial state
	# h: the heuristic function
	# return: the path from the initial state to the goal state

	# Initialize the open list
	open = []
	# Initialize the closed list
	closed = []
	# Initialize the path
	path = []

	path.append(state)

	# Add the initial state to the open list
	heapq.heappush(open, (h(state), state))

	while len(open) > 0:
		# Get the state with the lowest heuristic value
		(f, state) = heapq.heappop(open)
		
		# Add the state to the closed list
		closed.append(state)
		# If the state is the goal state, return the path
		if state == goal:
			return path

		# Get the children of the state
		children = GetChildren(state)
		for child in children:
			# If the child is not in the closed list, add it to the open list
			if child not in closed:
					heapq.heappush(open, (h(child) + len(path) + 1, child))
					# Add the child to the path
					path.append(child)

	# Return None if the goal state is not found
	return None


def main():
	# The main function

	# Get the initial state
	# state = input('Enter the initial state: ')
	state = '12B384765'
	# Get the search algorithm
	algorithm = input('Enter the search algorithm (BFS or A*): ')

	# Get the start time
	start = time.time()

	# Implement the search algorithm
	if algorithm == 'BFS':
		path = BestFirstSearch(state)
	elif algorithm == 'A*':
		path = AStarSearch(state)
	else:
		print('Invalid search algorithm')
		return
	
	# Get the end time
	end = time.time()

	# Print the path
	if path != None:
		print('The path is:')
		for i in range(len(path)):
			if i == 0:
				print(state, end = '')
			else:
				print('->' , state, end = '')

		print('\nThe number of states expanded is', len(path))
	else:
		print('The goal state is not found')
	print('The time taken is', end - start, 'seconds')
	

if __name__ == '__main__':
	main()