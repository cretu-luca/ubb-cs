function handleSubmit() {
    const input = document.getElementById("numbersInput").value

    let numbers = quickSort(parseInput(input))
    populateTable(numbers)
}

function populateTable(numbers) {
    let table = document.getElementById("table")
    table.innerHTML = ""

    let n = numbers.length / 5
    for (let i = 0; i < n; i++) {
        var rowNode = document.createElement("tr")
        
        for (let j = 0; j < 5; j++) {
            var cellNode = document.createElement("td")
            var textNode

            if (5 * n - i * 5 - j <= 0) {
                textNode = document.createTextNode("")
            }
            else {
                textNode = document.createTextNode(numbers[i * 5 + j])
            }

            cellNode.appendChild(textNode)
            rowNode.appendChild(cellNode)
        }

        table.appendChild(rowNode)
    }
}

function quickSort(numbers) {
    if (numbers.length <= 1) {
        return numbers
    }

    let pivot = numbers[0]
    let leftNumbers = []
    let rightNumbers = []

    for (let i = 1; i < numbers.length; i++) {
        if (numbers[i] < pivot) {
            leftNumbers.push(numbers[i])
        } else {
            rightNumbers.push(numbers[i])
        }
    }

    return [...quickSort(leftNumbers), pivot, ...quickSort(rightNumbers)]
}

function parseInput(input) {
    let numbers = input.match(/\d+/g)
    
    for(var i = 0; i < numbers.length; i++)
        numbers[i] = parseInt(numbers[i])

    return numbers

    /*
    const numbers = input.split(/[,;:. ]/);
    console.log(numbers);

    for (var i = 0; i < numbers.length; i++) {
        if (isNumber(numbers[i])) {
            numbers[i] = parseInt(numbers[i])
        } else {
            document.getElementById("error").innerHTML = "invalid"
            console.log("invalid")
        }
    }
    */
}

// test case: 200 8 20 1 28 21 6 4 84 62 0 9 3 74 66 2 19 48 72 100 85 101 
//            200 0 1 2 3 4 6 8 9 19 20 21 28 48 62 66 72 74 84 85 100 101