package Models;

import java.sql.ResultSet;
import java.sql.SQLException;

public class SpecialDeal{
	String code;
	int hoursvalid;
	Flight dealflight;
	int discount;
	String display() {
		return (code + " " + hoursvalid + " " + discount + "\n");
	}
	
	public void convert(ResultSet r) {
		try {
		code = r.getString("code");
		hoursvalid = Integer.parseInt(r.getString("hoursvalid"));
		discount = Integer.parseInt(r.getString("discount"));
		Flight f = new Flight();
		f.convert(r);
		dealflight = f;
		}
		catch(SQLException e) {
			e.printStackTrace();
		}
		
	}
	
}