class MonkeyBananaProblem:
    def __init__(self, initial_state, goal_state):
        self.initial_state = initial_state
        self.goal_state = goal_state

    def actions(self, state):
        possible_actions = []
        # Monkey can move if it is not at the same position as the box
        if state['monkey'] != state['box']:
            possible_actions.append('move')
        else:
            # Monkey can push the box if it is at the same position as the box
            possible_actions.append('push')
            # Monkey can climb if it is at the same position as the box and the banana
            if state['monkey'] == state['banana']:
                possible_actions.append('climb')
        return possible_actions

    def result(self, state, action):
        new_state = state.copy()
        if action == 'move':
            # Move monkey towards the box
            if state['monkey'] < state['box']:
                if state['monkey'] < 'C':
                    new_state['monkey'] = chr(ord(state['monkey']) + 1)
            elif state['monkey'] > state['box']:
                if state['monkey'] > 'A':
                    new_state['monkey'] = chr(ord(state['monkey']) - 1)
        elif action == 'climb':
            # Climb on the box
            new_state['monkey'] = 'on_box'
        elif action == 'push':
            # Push the box to the next position in the direction of the banana
            if state['monkey'] < state['banana']:
                if state['box'] < 'C':
                    new_state['monkey'] = chr(ord(state['monkey']) + 1)
                    new_state['box'] = chr(ord(state['box']) + 1)
            elif state['monkey'] > state['banana']:
                if state['box'] > 'A':
                    new_state['monkey'] = chr(ord(state['monkey']) - 1)
                    new_state['box'] = chr(ord(state['box']) - 1)
        return new_state

    def goal_test(self, state):
        return state == self.goal_state

def breadth_first_search(problem):
    frontier = [[problem.initial_state]]
    explored = set()
    while frontier:
        path = frontier.pop(0)
        current_state = path[-1]
        if problem.goal_test(current_state):
            return path
        explored.add(tuple(current_state.items()))
        for action in problem.actions(current_state):
            new_state = problem.result(current_state, action)
            if tuple(new_state.items()) not in explored:
                new_path = path + [new_state]
                frontier.append(new_path)
    return None

# Updated initial and goal states for a solvable problem
initial_state = {'monkey': 'A', 'box': 'B', 'banana': 'C'}
goal_state = {'monkey': 'on_box', 'box': 'C', 'banana': 'C'}

if __name__ == "__main__":
    problem = MonkeyBananaProblem(initial_state, goal_state)
    solution = breadth_first_search(problem)
    if solution:
        print("Solution found:")
        for state in solution:
            print(state)
    else:
        print("No solution found.")
