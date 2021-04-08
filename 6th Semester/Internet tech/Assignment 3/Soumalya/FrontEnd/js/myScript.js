
//var journeyDate = document.getElementById("journey_date")
//console.log("Boooom: ", journeyDate.getAttribute("placeholder"))
//console.log(journeyDate.value)
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

function compare(dateShown, offerDate)
{
    // dateShown= mm/dd/2021 and string
    // offerdate = yyyy-mm-dd
    // substring(1,4) => starting 1th char and taking 4 chars

    dateDD = dateShown.substring(3,5)
    offerDD = offerDate.substring(8)
    //console.log("dateDD, offerDD => ", dateDD, " ", offerDD)

    dateMM = dateShown.substring(0,2)
    offerMM = offerDate.substring(5,7)
    //console.log("dateMM, offerMM => ", dateMM, " ", offerMM)

    dateYY = dateShown.substring(6)
    offerYY = offerDate.substring(0,4)
    //console.log("dateYY, offerYY => ", dateYY, " ", offerYY)


    if((dateDD === offerDD) && (dateMM === offerMM) && (dateYY === offerYY))
        return true
    
    
    return false
}


var datepicker = document.getElementById("datepicker")
var dateToBeShown, response, isFromDeals = false;
var getDealsButton = document.getElementById("get_deals")

getDealsButton.addEventListener('click', function (event) {

    if (!dateToBeShown) alert("Select a date")
    else {
        
        // fetch data from backend when get deals bttn is pressed
        console.log(dateToBeShown)
        axios.get("http://localhost:8080/Airflight/deals").then(res=> {

            newSetOfDeals = []
            //console.log(res.data)
            var i;
            for(i=0; i<(res.data).length ; i++)
            {
                //console.log("fetched: ", (res.data)[i].offerDate)
                if(compare(dateToBeShown, (res.data)[i].offerDate))
                {
                    newSetOfDeals.push((res.data)[i])
                }
            }


            //console.log("new deals: " + newSetOfDeals)
            transitionData(newSetOfDeals)
            blockData(newSetOfDeals.slice(2))
        })
        
    }
})

datepicker.addEventListener("click", function (event) {

    // first set date then click on calender icon and then 
    if (event.target.value) {
        dateToBeShown = event.target.value
    }

    //console.log("Boooom: ", dateToBeShown)
    // Boooom:  04/03/2021 - mm/dd/yyyy
})




window.onload = allData.bind(event)


function allData() {
    axios.get("http://localhost:8080/Airflight/deals").then(res=> {

        //console.log(res.data)
        transitionData(res.data)
        blockData((res.data).slice(2))
    })
    
}

function transitionData(deals) {
    var transitionImageTitle1 = document.getElementById("first_transition_title")
    var transitionImageImage1 = document.getElementById("first_transition_image")
    var transitionImagePrice1 = document.getElementById("first_transition_price")
    var transitionImageButton1 = document.getElementById("first_transition_button")

    var transitionImageTitle2 = document.getElementById("second_transition_title")
    var transitionImageImage2 = document.getElementById("second_transition_image")
    var transitionImagePrice2 = document.getElementById("second_transition_price")
    var transitionImageButton2 = document.getElementById("second_transition_button")

    var transitionImageTitle3 = document.getElementById("third_transition_title")
    var transitionImageImage3 = document.getElementById("third_transition_image")
    var transitionImagePrice3 = document.getElementById("third_transition_price")
    var transitionImageButton3 = document.getElementById("third_transition_button")


    transitionImageTitle1.innerText = deals[0].destCity
    transitionImageTitle2.innerText = deals[1].destCity
    transitionImageTitle3.innerText = deals[2].destCity

    //console.log(imageName)
    //blockImageImage1.data - src = "/images/ban_img3.jpg"
    //console.log(blockImageImage)
    transitionImagePrice1.innerText = deals[0].cost
    transitionImagePrice2.innerText = deals[1].cost
    transitionImagePrice3.innerText = deals[2].cost

    // blockImageImage1.src = deals[0].image
    // blockImageImage2.src = deals[1].image
    // blockImageImage3.src = deals[2].image


    transitionImageButton1.addEventListener('click', addDestCity.bind(event,deals[0]))
    transitionImageButton2.addEventListener('click', addDestCity.bind(event,deals[1]))
    transitionImageButton3.addEventListener('click', addDestCity.bind(event,deals[2]))
}

function blockData(deals) {

    //e.preventDefault();
    // console.log("FIRING...")
    // console.log("title:", title, "\n", "ImageName: ", imageName, "\n", price)

    var blockImageTitle1 = document.getElementById("first_block_title")
    var blockImageImage1 = document.getElementById("first_block_image")
    var blockImagePrice1 = document.getElementById("first_block_price")
    var blockImageButton1 = document.getElementById("first_block_button")

    var blockImageTitle2 = document.getElementById("second_block_title")
    var blockImageImage2 = document.getElementById("second_block_image")
    var blockImagePrice2 = document.getElementById("second_block_price")
    var blockImageButton2 = document.getElementById("second_block_button")

    var blockImageTitle3 = document.getElementById("third_block_title")
    var blockImageImage3 = document.getElementById("third_block_image")
    var blockImagePrice3 = document.getElementById("third_block_price")
    var blockImageButton3 = document.getElementById("third_block_button")


    blockImageTitle1.innerText = deals[0].destCity
    blockImageTitle2.innerText = deals[1].destCity
    blockImageTitle3.innerText = deals[2].destCity

    //console.log(imageName)
    //blockImageImage1.data - src = "/images/ban_img3.jpg"
    //console.log(blockImageImage)
    blockImagePrice1.innerText = deals[0].cost
    blockImagePrice2.innerText = deals[1].cost
    blockImagePrice3.innerText = deals[2].cost

    blockImageImage1.src = getRandomImage()
    blockImageImage2.src = getRandomImage()
    blockImageImage3.src = getRandomImage()


    blockImageButton1.addEventListener('click', addDestCity.bind(event, deals[0]))
    blockImageButton2.addEventListener('click', addDestCity.bind(event, deals[1]))
    blockImageButton3.addEventListener('click', addDestCity.bind(event, deals[2]))

}

var cityId = 0;
function addDestCity(response ) {
    // get the destination form field and put the data into that
    var destCityInput = document.getElementById("destCityInput")
    var boardingCityInput = document.getElementById("boardingCityInput")
    var priceTag = document.getElementById("price_tag")

    destCityInput.value = response.destCity
    boardingCityInput.value = response.sourceCity
    priceTag.innerText = '₹'+ (response.cost).toString()
    cityId = response.id
    console.log(cityId)
    //console.log(typeof response.cost)

    // mark that the user wants a deal
    isFromDeals = true

}

/////////////////////scraped radio buttons/////////////////////

// event listeners for radio buttons
// var economyButton = document.getElementById("tmRadio0")
// var bussinessButton = document.getElementById("tmRadio1")
// var luxuryButton = document.getElementById("tmRadio2")


// economyButton.addEventListener('change', function(event){
//     console.log(economyButton.getAttribute("value"))
//     console.log("Clicked meeeee")
// })

// bussinessButton.addEventListener('change', function(event){
//     console.log(bussinessButton.getAttribute("value"))
//     console.log("Clicked meeeee")
// })

// var radios = document.getElementsByName("Comfort");
// console.log(radios)
// var prev = null

// for(var i=0; i< radios.length; i++)
// {
//     radios[i].addEventListener('change', function(){
//         (prev) ? console.log(prev.value) : null;
//         if(this !== prev){
//             prev = this
//         }
            
        
//         console.log("here: ", this.value)
//     })
// }

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

// isFromDeals is a bool value defining if the user wants a special deal or not.
// if so, then redirect to booking site
// if not redirect to filtering part

var bookFlightButton = document.getElementById("book_flight")
bookFlightButton.addEventListener('click', function(){

    var destCityInput = document.getElementById("destCityInput").value
    var boardingCityInput = document.getElementById("boardingCityInput").value

    if(isFromDeals)
    {
        // redirect to upcoming tours
        bookFlightButton.href = "index-2.html?id=" + `${cityId}`
    }
    else
    {
        // redirect to filtering page
        bookFlightButton.href = "index-1.html?dest=" + `${destCityInput}` +"&source=" + `${boardingCityInput}` +"&date=" + `${dateToBeShown}`
    }
})

// http://127.0.0.1:5500/index-1.html?dest=Delhi&source=Kolkata