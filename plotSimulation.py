from matplotlib import pyplot as plt

def main():

    rayXPositions = []
    rayYPositions = []
    
    with open("RayCoordinates.txt") as rayCoordinates:
        rayLines = rayCoordinates.readlines()

    for line in rayLines:
        line = line.rstrip()
        splitLine = line.split(",")
        rayXPositions.append(float(splitLine[0]))
        rayYPositions.append(float(splitLine[1]))

    prismXPositions = []
    prismYPositions = []

    with open("PrismCoordinates.txt") as prismCoordinates:
        prismLines = prismCoordinates.readlines()

    for line in prismLines:
        line = line.rstrip()
        splitLine = line.split(",")
        prismXPositions.append(float(splitLine[0]))
        prismYPositions.append(float(splitLine[1]))  

    print(rayXPositions)
    print(rayYPositions)

    print(prismXPositions)
    print(prismYPositions)

    figure = plt.figure()
    axes = plt.axes()

    plt.xlim(0, 500)
    plt.ylim(0, 500)

    prismStartX = prismXPositions[0]
    prismStartY = prismYPositions[0]
    prismXPositions.append(prismStartX)
    prismYPositions.append(prismStartY)

    plt.plot(prismXPositions, prismYPositions)
    plt.plot(rayXPositions, rayYPositions)

    plt.show()

if __name__ == "__main__":
    main()