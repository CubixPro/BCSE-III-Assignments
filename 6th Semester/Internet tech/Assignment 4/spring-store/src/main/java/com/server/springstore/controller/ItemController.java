package com.server.springstore.controller;

import java.util.List;
import javax.servlet.http.HttpSession;

import com.server.springstore.db.ItemRepository;
import com.server.springstore.db.UserRepository;
import com.server.springstore.model.Item;
import com.server.springstore.model.User;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Sort;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@CrossOrigin(origins = "http://localhost:3000")
@RestController
@RequestMapping("/items")
public class ItemController {
    
    @Autowired
    private ItemRepository itemRepo;

    @Autowired
    private UserRepository userRepo;

    @GetMapping("/getAll")
    public List<Item> getItems(HttpSession session) {
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
		System.out.println(auth.getName());

		User user = userRepo.findByEmail(auth.getName());
		System.out.println(user);

		String preference = (String)session.getAttribute("preference");
		if(preference == null){
			session.setAttribute("preference",user.getPreference());
			System.out.println((String)session.getAttribute("preference"));

			preference = (String)session.getAttribute("preference");
			Sort sort = Sort.by("fdiscount").descending();
			//if(preference.equals("New arrivals"))
			if(preference.equals("latest"))
				sort = Sort.by("latest").descending();
			return itemRepo.findAll(sort);
		}
		else{

			Sort sort;

			if(preference.equals("latest")) {
				sort = Sort.by("latest").descending();
			}
			else {
				sort = Sort.by("fdiscount").descending();
			}
			return itemRepo.findAll(sort);
		}
    }

    @GetMapping("/searchKey")
    public List<Item> searchItems(@RequestParam("check") String check) {
        return itemRepo.findByCtype(check);
	}
	
	@PostMapping("/preferences")
	public Item prefItem(@RequestBody Item item, HttpSession session) {
		String val = (String)session.getAttribute("prefVal");
		int x=0;
		if(val == null)
			x=0;
		else
			x=Integer.parseInt(val);

		if(item.getFdiscount()==0) {
			x++;
		}

		else {
			x--;
		}

		if(x>=0)
			session.setAttribute("preference", "latest");
		else
			session.setAttribute("preference", "discount");

		String ke = String.valueOf(x);
		session.setAttribute("prefVal", ke);

		return item;
	}
}
