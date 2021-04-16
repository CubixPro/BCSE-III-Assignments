package com.Airflight.deals;


import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;


import java.util.*;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

class Offer
{
	private String sourceCity, destCity;
	private int cost, legs, id;
	private ArrayList<String> legDest;
	
	private String journeyDate, journeyTime, offerDate;
	// needed date, start time and endtime attributes
	
	private String startTime, endTime, carrier; // start and end time are strings in 24 format 20:00
	public Offer() {}
	
	public Offer(int id, String sourceCity, String destCity, int cost,int legs, String journeyDate, String journeyTime, String offerDate, String startTime, String endTime, String carrier)
	{
		this.id 			= id;
		this.sourceCity 	= sourceCity;
		this.destCity		= destCity;
		this.cost 			= cost;
		this.legs			= legs;
		this.journeyDate	= journeyDate;
		this.journeyTime	= journeyTime;
		this.offerDate		= offerDate;
		this.startTime		= startTime;
		this.endTime		= endTime;
		this.carrier		= carrier;

	}
	
	public void convert(ResultSet rs)
	{
		try {
			
			this.id 			= Integer.parseInt(rs.getString("id"));
			this.sourceCity 	= rs.getString("source");
			this.destCity		= rs.getString("dest");
			this.cost 			= Integer.parseInt(rs.getString("cost"));
			this.legs			= Integer.parseInt(rs.getString("legs"));
			this.journeyDate	= rs.getString("journeyDate");
			this.journeyTime	= rs.getString("journeyTime");
			this.offerDate		= rs.getString("offerDate");
			this.startTime		= rs.getString("offerStartTime");
			this.endTime 		= rs.getString("offerEndTime");
			this.carrier 		= rs.getString("carrier");
			//this.legDest		= new ArrayList<String>(){{add("Mumbai"); add("Chennai");}};
			//this.status			= "Hello I am fine atleast";
			
		}catch(SQLException e)
		{
			System.out.println("Line 78");
			e.printStackTrace();
		}
	}
}


class OfferList
{
	private ArrayList<Offer> arrayList;
	
	public OfferList()
	{
		this.arrayList = new ArrayList<>();
	}
	
	public void addOffertoList(int id, String sourceCity, String destCity, int cost,int legs, String journeyDate, String journeyTime, String offerDate, String startTime, String endTime, String carrier)
	{
		Offer newOffer = new Offer(id, sourceCity, destCity, cost, legs, journeyDate, journeyTime, offerDate, startTime, endTime, carrier);
		arrayList.add(newOffer);
	}
	
	public ArrayList<Offer> getOfferList()
	{
		return this.arrayList;
	}
}


@WebServlet("/deals")
public class DealsOfTheDay extends HttpServlet {
	
	protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException
	{
		res.setContentType("application/json");

		PrintWriter out = res.getWriter();
		
		
		ArrayList<Offer> offerList = new ArrayList<Offer>();
////////////////////////////////// DB connection ///////////////////////////
		Connection connection = null;
		
		try {
			
			Class.forName("org.postgresql.Driver");
			connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/FlightDB", "postgres", "soumalya@10");
			
			if(connection != null)
				System.out.println("Hey hello high yoo");
			else 
				System.out.println("Nopeeeeeeeeeeeeeeee!");
			
		} catch (Exception e) {
			// TODO: handle exception
			System.out.println("Line 105");
			System.out.println(e);
		}
		
		String query = "select * from \"SpecialDeals\"";
		

		
		
		try {
			Statement st= connection.createStatement();
			ResultSet rs = st.executeQuery(query);
			
			while(rs.next()) {
	  			Offer offer = new Offer();
	  			offer.convert(rs);
	  			offerList.add(offer);
	  			//System.out.println("BoomBaamBoomBaam");
	  		}
			
			st.close();
			//connection.close();
			
		} catch (SQLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		

//////////////////////////////////////////////////////////////////	
		
		
		//offerList.add(new Offer(5,"Kolkata","Banglore", 2500, 2, "22-04-2021", "07:30", "04-04-2021","11:00", "17:00", "GoIndia"));
		
		GsonBuilder gsonBuilder = new GsonBuilder().setPrettyPrinting();
		Gson gson = gsonBuilder.create();
		String jsonObj = gson.toJson(offerList);
		out.print(jsonObj);
		
		out.flush();
		try {
			connection.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}