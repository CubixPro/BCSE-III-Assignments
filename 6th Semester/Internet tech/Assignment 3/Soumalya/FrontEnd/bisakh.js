/*
Author: Bisakh Mondal

**Don't cut the header, I repeat don't🤡.
*/

//const fs = require('fs')

const NumEntries = 40

const departures = []

const airports = ["Kolkata (CCU)", "Delhi (DEL)", "Mumbai (BOM)", "Bangalore (BLR)", "Chennai (CAA)", "Hyderabad (HYD)", "Guwahati (GAU)", "Pune(PNU)"]

function getRandomInt(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

for (let i = 0; i < NumEntries; i++) {
    const idx = getRandomInt(0, airports.length - 1)
    let idx1 = idx

    while (idx === idx1) {
        idx1 = getRandomInt(0, airports.length - 1)
    }

    let hops = new Set()

    //50 % chance for flight to have a hop
    if (Math.random() > 0.5) {
        const hopsNum = getRandomInt(1, airports.length - 2)
        for (let z = 0; z < hopsNum; z++) {
            const rint = getRandomInt(0, airports.length - 1)
            if (rint !== idx1 && rint !== idx) {
                hops.add(rint)
            }
        }
    }

    const schema = {
        source: airports[idx],
        destination: airports[idx1],
        hops: Array.from(hops).map(d => airports[d])
    }

    departures.push(schema)
}

fs.writeFileSync("./heyBitch.json", JSON.stringify(departures), 'utf8', (err) => {
    if (err) throw new Error("Throw away ur pc! bitch")
})
console.log("Hey SweetAss!! JSON has been successfully saved to dicks...")