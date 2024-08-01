let unempRate = 0.037  /** Current Unemployment Rate, converted to decimal. Ex. 0.037 = 3.70% Unemployment */
let maxBen = 665.00   /** Current maximum weekly benefit amount in USD */
let maxWeeks = 16     /** Current maximum number of benefit weeks */
let benPerc = 0.011923 /** Current weekly benefit amount percentage, converted to decimal. Ex. 0.0119 = 1.19% */

/** ^^^^^^^^^^^^^^^^^^ EDIT THESE VALUES AS NEEDED TO CHANGE CALCULATOR FORMULAS ----------------------- */

let formatting_options = {
    style:'currency',
    currency: 'USD',
    minimumFractionDigits:2,
}

var dollarString = new Intl.NumberFormat("en-US", formatting_options)

function shareCalc() {
    var numEmps = document.getElementById("empInput").value
    var numLayoff = document.getElementById("layoffInput").value 
    var numPart = document.getElementById("partInput").value 
    var numHours = document.getElementById("hoursInput").value 
    var aveSal = document.getElementById("salInput").value 
    
    var layoffCharges = ((numLayoff * maxBen) * maxWeeks)
    var KYWSCharges = (((numPart * maxBen) * (numHours / 40)) * maxWeeks)
    var KYWSSavings = (layoffCharges - KYWSCharges)

    var weeklySal = aveSal
    var weeklyBen = ((weeklySal * 52) * benPerc)

    if (weeklyBen > maxBen) {
        var layoffLoss = (maxBen - weeklySal)
    } else {
        var layoffLoss = (weeklyBen - weeklySal)
    }

    if (weeklyBen > maxBen) {
        var KYWSLoss = (maxBen * (numHours / 40) - (aveSal * (numHours / 40)))
    } else {
        var KYWSLoss = (weeklyBen * (numHours / 40) - (aveSal * (numHours / 40)))
    }

    var employerResults = document.getElementById("employerResults")
    var employeeResults = document.getElementById("employeeResults")
    
    var layoffChargesRow = employerResults.getElementsByTagName("tr")[1]
    var layoffChargesCell = layoffChargesRow.getElementsByTagName("td")[1]

    var KYWSChargesRow = employerResults.getElementsByTagName("tr")[2]
    var KYWSChargesCell = KYWSChargesRow.getElementsByTagName("td")[1]

    var KYWSSavingsRow = employerResults.getElementsByTagName("tr")[3]
    var KYWSSavingsCell = KYWSSavingsRow.getElementsByTagName("td")[1]

    var weeklySalRow = employeeResults.getElementsByTagName("tr")[1]
    var weeklySalCell = weeklySalRow.getElementsByTagName("td")[1]

    var weeklyBenRow = employeeResults.getElementsByTagName("tr")[2]
    var weeklyBenCell = weeklyBenRow.getElementsByTagName("td")[1]

    var layoffLossRow = employeeResults.getElementsByTagName("tr")[3]
    var layoffLossCell = layoffLossRow.getElementsByTagName("td")[1]

    var KYWSLossRow = employeeResults.getElementsByTagName("tr")[4]
    var KYWSLossCell = KYWSLossRow.getElementsByTagName("td")[1]


    layoffChargesCell.innerHTML = dollarString.format(layoffCharges)
    KYWSChargesCell.innerHTML = dollarString.format(KYWSCharges)
    KYWSSavingsCell.innerHTML = dollarString.format(KYWSSavings)

    if (KYWSSavings > 0) {
        document.getElementById("KYWSSavingsLabel").innerHTML = "Total KYWS program savings"
    } else if (KYWSSavings < 0) {
        document.getElementById("KYWSSavingsLabel").innerHTML = "Total KYWS program losses"
    } else {
        document.getElementById("KYWSSavingsLabel").innerHTML = "Total KYWS program savings/losses"
    }
    
    weeklySalCell.innerHTML = dollarString.format(weeklySal)
    
    if (weeklyBen > maxBen) {
        weeklyBenCell.innerHTML = dollarString.format(maxBen)
    } else {
        weeklyBenCell.innerHTML = dollarString.format(weeklyBen)
    }

    layoffLossCell.innerHTML = dollarString.format(layoffLoss)
    KYWSLossCell.innerHTML = dollarString.format(KYWSLoss)

}

function dataPop() {
    document.getElementById("unemploymentRate").innerHTML = parseFloat(unempRate * 100).toPrecision(3) + "%"
    document.getElementById("maximumWeeks").innerHTML = maxWeeks
    document.getElementById("weeklyBenPerc").innerHTML = parseFloat(benPerc * 100).toPrecision(5) + "%"
    document.getElementById("maxWeeklyBen").innerHTML = dollarString.format(maxBen)
}

window.onload = function() {
    dataPop();
}

function resetCalc() {
    document.getElementById("empInput").value = ""
    document.getElementById("layoffInput").value = ""
    document.getElementById("partInput").value = ""
    document.getElementById("hoursInput").value = ""
    document.getElementById("salInput").value = ""

    layoffChargesCell.innerHTML = ""
    KYWSChargesCell.innerHTML = ""
    KYWSSavingsCell.innerHTML = ""
    weeklySalCell.innerHTML = ""
    document.getElementById("WeeklyBenCell").innerHTML = ""
    layoffLossCell.innerHTML = ""
    KYWSLossCell.innerHTML = ""

    document.getElementById("KYWSSavingsLabel").innerHTML = "Total KYWS program savings/losses"
}