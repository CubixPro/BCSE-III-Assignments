
{/* 
<div class="grid_4">
	<div class="banner">
		<img src="images/page2_img1.jpg" alt="">
		<div class="label">
			<div class="title">NEW ZEALAND</div>
			<div class="price">from<span>$ 1.200</span></div>
            <div>On<span>Date</span></div>
            <div>at<span>Time</span></div>
            <div>with<span>legs</span>legs</div>
            
			<a href="#">LEARN MORE</a>
		</div>
	</div>
</div> */}
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
// create this element using js


//console.log(newElement)

// get banners and empty_div


// for(var i = 0; i< 10; i++)
// {
//     var newBan = createNewElement("images/page2_img1.jpg", "Norway", "Delhi", "15000" )
//     banners.insertBefore(newBan, emptyDiv)
// }


//createNewElement("images/page2_img1.jpg", "Norway", "Delhi", "15000" )
// const { name, room } = queryString.parse(location.search);
 // returns a json and we are restructing the object to name=name and room=room
// we also could have const data = ... and data.room or data.name


// const { dest, source } = queryString.parse(location.search);
// console.log(dest, source)

function getParameterByName(name, url = window.location.href) {
    name = name.replace(/[\[\]]/g, '\\$&');
    var regex = new RegExp('[?&]' + name + '(=([^&#]*)|&|#|$)'),
        results = regex.exec(url);
    if (!results) return null;
    if (!results[2]) return '';
    return decodeURIComponent(results[2].replace(/\+/g, ' '));
}


var dest = getParameterByName("dest")
var source = getParameterByName("source")
var date = getParameterByName("date")

console.log(dest, source, date)


var newSetOfDeals = [];



// searches on flight data
function searchByDest(response)
{
    if(dest !== null && source !== null)
    {
        var localDest = dest.trim().toLowerCase()
        var localSource = source.trim().toLowerCase()

        // filter based on these
        newSetofDeals = []
        for(var i=0; i< response.length; i++)
        {
            var flightDest = (response[i].destCity).trim().toLowerCase()
            var flightSource = (response[i].sourceCity).trim().toLowerCase()

            if((localDest === flightDest) && (localSource === flightSource))
            {
                newSetofDeals.push(response[i])
            }
        }


        // insert in dom
        for(var i=0; i<newSetofDeals.length; i++)
        {
            var nowDest = newSetofDeals[i].destCity
            var nowSource = newSetofDeals[i].sourceCity
            var nowPrice = newSetofDeals[i].cost
            var journeyDate = newSetofDeals[i].journeyDate
            var journeyTime = newSetofDeals[i].journeyTime
            var carrier = newSetofDeals[i].carrier
            var legs = newSetofDeals[i].legs
            var randomImage = getRandomImage()
            createNewElement(randomImage, nowDest, nowSource, nowPrice, journeyDate, journeyTime, carrier, legs)
        }
    }

    else{

        newSetofDeals = []
        console.log("Search and dest are null")
        console.log(dest, source)
        for(var i=0; i<response.length; i++)
        {
            newSetofDeals.push(response[i])
            console.log("newSetofval in search dest: ", newSetOfDeals, "Response[i]: ", response[i])// for next search on time
            var nowDest = response[i].destCity
            var nowSource = response[i].sourceCity
            var nowPrice = response[i].cost
            var journeyDate = newSetofDeals[i].journeyDate
            var journeyTime = newSetofDeals[i].journeyTime
            var carrier = newSetofDeals[i].carrier
            var legs = newSetofDeals[i].legs
            var randomImage = getRandomImage()
            createNewElement(randomImage, nowDest, nowSource, nowPrice, journeyDate, journeyTime, carrier, legs)
        }

        //console.log("newSetofval in search dest: ", newSetOfDeals)
    }
}


window.onload = showResults.bind(event)
function showResults()
{
    // search based on dest, source 
    axios.get("http://localhost:8080/Airflight/flights").then(res=> {

        //console.log(res.data)
        searchByDest(res.data)
    })
}

const searchDestButton = document.getElementById("searchDestButton")
searchDestButton.addEventListener('click', function(event){

    var tempDestInput = document.getElementById("destCitySearchInput")
    var tempSourceInput = document.getElementById("boardingCitySearchInput")


    console.log(tempDestInput, tempSourceInput)

    if(tempDestInput !== null && tempSourceInput !== null)
    {
        dest = tempDestInput.value
        source = tempSourceInput.value
    }
    else
    {
        dest = null
        source = null
    }
    console.log("dest: ", dest, "source: ", source)

    // delete the child and then add the search data
    

    var myNode = document.getElementById("banners")
    deleteChilds(myNode)
    
    // node list er 7th index theke 18th index obdhi delete korte hobe
    // upto 6th index and last 2 index should remain

    showResults()
    console.log(myNode.childNodes)
})

// delete child of a node
function deleteChilds(myNode)
{
    // last length should be 9
    while((myNode.childNodes).length > 9)
    {
        myNode.removeChild((myNode.childNodes)[7])
    }
}




//console.log(dest, source, date)
function searchByTime()
{
    // new set of deals contains the current showing bostus

    var temp = []
    var searchByTimeInput = document.getElementById("timeInput")
    var timeValue = searchByTimeInput.value
    console.log("time value: ", typeof timeValue)
    console.log(newSetOfDeals)
    if(timeValue.length === 0)
    {
        alert("Plz enter a valid time in 24 hour format!")
    }

    if(newSetOfDeals.length > 0)
    {
        // keu to ache
        for(var i=0; i<newSetOfDeals.length; i++)
        {
            var journeyTime = newSetOfDeals[i].journeyTime
            if(compare(timeValue, journeyTime))
            {
                temp.push(newSetOfDeals[i])
            }
        }
    }

    // delete the childs
    var myNode = document.getElementById("banners")
    deleteChilds(myNode)

    console.log("Cleared dom!")
    

    newSetOfDeals = []
    newSetOfDeals = temp.slice()

    console.log(newSetOfDeals)
    // creteElements that are in newsetofdeals

    for(var i=0; i<newSetofDeals.length; i++)
    {
        var nowDest = newSetofDeals[i].destCity
        var nowSource = newSetofDeals[i].sourceCity
        var nowPrice = newSetofDeals[i].cost
        var journeyDate = newSetofDeals[i].journeyDate
        var journeyTime = newSetofDeals[i].journeyTime
        var carrier = newSetofDeals[i].carrier
        var legs = newSetofDeals[i].legs

        var randomImage = getRandomImage()
        
        createNewElement(randomImage, nowDest, nowSource, nowPrice, journeyDate,journeyTime, carrier, legs )
    }


}

///////////////////////////////////////////////////////////
// search by time
var searchByTimeButton = document.getElementById("searchTimeButton")
searchByTimeButton.addEventListener('click', function(){

    searchByTime();

})

function compare(timeShown, journeyTime)
{
   
    hourTimeShown = timeShown.substring(0,2)
    hourTimeShownNumber = parseInt(hourTimeShown, 10)

    hourTimeJourney = journeyTime.substring(0,2)
    hourTimeShownNumber = parseInt(hourTimeJourney, 10)

    console.log(hourTimeShownNumber, hourTimeShownNumber)

    // if within 2 hours....return true
    if(hourTimeJourneyNumber - hourTimeJourney <= 3) {return true;}
    
    return false;
}