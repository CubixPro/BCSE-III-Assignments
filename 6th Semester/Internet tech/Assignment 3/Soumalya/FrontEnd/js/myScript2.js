function randomIntFromInterval(min, max) { // min and max included 
    return Math.floor(Math.random() * (max - min + 1) + min);
}

var imageNames = [
   
    "images/ban_img1.jpg",
    "images/ban_img2.jpg",
    "images/ban_img3.jpg",
    "images/page2_img1.jpg",
    "images/page2_img2.jpg",
    "images/page2_img3.jpg",
    "images/page2_img4.jpg",
    "images/page2_img5.jpg",
    "images/page2_img6.jpg",
    "images/page2_img7.jpg",
    "images/page2_img8.jpg",
    "images/page3_img1.jpg",
    "images/page3_img2.jpg",
    "images/page3_img3.jpg",
]


function getRandomImage()
{
    var num = randomIntFromInterval(0, imageNames.length-1)
    return imageNames[num]
}








// function createNewElement(imageName, destCity, sourceCity, price)
// {
//     var newElement = document.createElement('div')
//     newElement.className = "grid_4"


//     var bannerDiv = document.createElement('div')
//     bannerDiv.className = "banner"

//     var imgElement = document.createElement('img')
//     imgElement.src = `${imageName}`
//     imgElement.alt = "Sorry"

//     var labelDiv = document.createElement('div')
//     labelDiv.className = "label"

//     var titleDiv = document.createElement('div')
//     titleDiv.className = "title"
//     titleDiv.innerText = `${destCity}`

//     var priceDiv = document.createElement('div')
//     priceDiv.className = "price"
//     priceDiv.innerHTML = `from ${sourceCity}<span>₹${price}</span>`

//     var aLink = document.createElement('a')
//     aLink.href = "#"
//     aLink.innerText="Learn More"

//     labelDiv.appendChild(titleDiv)
//     labelDiv.appendChild(priceDiv)
//     labelDiv.appendChild(aLink)

//     bannerDiv.appendChild(imgElement)
//     bannerDiv.appendChild(labelDiv)

//     newElement.appendChild(bannerDiv)

//     var newBan = newElement.cloneNode(true)

//     var banners = document.getElementById("banners")
//     var emptyDiv = document.getElementById("empty_div")

//     banners.insertBefore(newBan, emptyDiv)
// }


function createNewElement(imageName, destCity, sourceCity, price, journeyDate, journeyTime,carrier, legs)
{
    var newElement = document.createElement('div')
    newElement.className = "grid_4"


    var bannerDiv = document.createElement('div')
    bannerDiv.className = "banner"

    var imgElement = document.createElement('img')
    imgElement.src = `${imageName}`
    imgElement.alt = "Sorry"

    var labelDiv = document.createElement('div')
    labelDiv.className = "label"

    var titleDiv = document.createElement('div')
    titleDiv.className = "title"
    titleDiv.innerText = `${destCity}`

    var priceDiv = document.createElement('div')
    priceDiv.className = "price"
    priceDiv.innerHTML = `from ${sourceCity}<span>₹${price}</span>`

    var dateDiv = document.createElement('div')
    dateDiv.className = "date"
    dateDiv.innerHTML = `On <span>${journeyDate}</span>`

    var timeDiv = document.createElement('div')
    timeDiv.className = "time"
    timeDiv.innerHTML = `at <span>${journeyTime}</span>`

    var legsDiv = document.createElement('div')
    legsDiv.className = "legs"
    legsDiv.innerHTML = `with <span>${legs}</span> legs`

    var aLink = document.createElement('a')
    aLink.href = "#"
    aLink.innerText="Book Flight"
    aLink.addEventListener('click', function()
    {
        console.log("JourneyDate: ", journeyDate)
        console.log("JourneyTime: ", journeyTime)
        console.log("Carrier: ", carrier)
    })

    labelDiv.appendChild(titleDiv)
    labelDiv.appendChild(priceDiv)
    labelDiv.appendChild(dateDiv)
    labelDiv.appendChild(timeDiv)
    labelDiv.appendChild(legsDiv)
    labelDiv.appendChild(aLink)

    bannerDiv.appendChild(imgElement)
    bannerDiv.appendChild(labelDiv)

    newElement.appendChild(bannerDiv)

    var newBan = newElement.cloneNode(true)

    var banners = document.getElementById("banners")
    var emptyDiv = document.getElementById("empty_div")

    banners.insertBefore(newBan, emptyDiv)
}

function getParameterByName(name, url = window.location.href) {
    name = name.replace(/[\[\]]/g, '\\$&');
    var regex = new RegExp('[?&]' + name + '(=([^&#]*)|&|#|$)'),
        results = regex.exec(url);
    if (!results) return null;
    if (!results[2]) return '';
    return decodeURIComponent(results[2].replace(/\+/g, ' '));
}


var id = getParameterByName("id")

window.onload = showJourney.bind(event)

function showJourney()
{
    if(id === null)
    {
        var emptyDiv = document.getElementById("empty_div")
        emptyDiv.innerHTML = `<h5>You don't have any upcoming journeys </h5>`
    }
    else
    {
        axios.get("http://localhost:8080/Airflight/deals").then(res=> {

            for(var i=0; i< (res.data).length; i++)
            {
                if(id == (res.data)[i].id)
                {
                    var imageName = getRandomImage()
                    createNewElement(imageName, (res.data)[i].destCity, (res.data)[i].sourceCity, (res.data)[i].cost, (res.data)[i].journeyDate, (res.data)[i].journeyTime, (res.data)[i].carrier, (res.data)[i].legs)
                }
            }
        })
    }
}
