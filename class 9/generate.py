import random

def generate_input():
    n = 4
    # Generate the 4x4 matrix with random numbers between 0 and 10
    matrix = [[random.randint(10, 20) for _ in range(n)] for _ in range(n)]
    
    # Generate random update commands
    commands = []
    for _ in range(n):
        c = random.choice(['U', 'D'])
        i = random.randint(1, n)
        j = random.randint(1, n)
        commands.append((c, i, j))
    
    # Write the generated input to input.txt
    with open('input.txt', 'w') as f:
        f.write(f"{n}\n")
        for row in matrix:
            f.write(' '.join(map(str, row)) + '\n')
        for command in commands:
            f.write(f"{command[0]} {command[1]} {command[2]}\n")

generate_input()