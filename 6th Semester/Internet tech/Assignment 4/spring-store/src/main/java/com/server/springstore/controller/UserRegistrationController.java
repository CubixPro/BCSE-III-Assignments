package com.server.springstore.controller;

import com.server.springstore.controller.dto.UserRegistrationDto;
import com.server.springstore.service.UserService;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class UserRegistrationController {
    private UserService userService;

    public UserRegistrationController(UserService userService) {
        super();
        this.userService = userService;
    }

    @ModelAttribute("user")
    public UserRegistrationDto userRegistrationDto() {
        return new UserRegistrationDto();
    }

    @GetMapping("/registration")
    public String showRegistrationForm() {
        return "registration";
    }

    @PostMapping("/registration")
    public String registerUserAccount(@ModelAttribute("user") UserRegistrationDto registrationDto) {
        userService.save(registrationDto);
        return "redirect:/registration?success";
    }

    @GetMapping("/login")
    public String login() {
        return "login";
    }

}
