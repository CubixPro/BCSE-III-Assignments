package com.server.springstore.service;

import com.server.springstore.controller.dto.UserRegistrationDto;
import com.server.springstore.model.User;

import org.springframework.security.core.userdetails.UserDetailsService;

public interface UserService extends UserDetailsService {
    User save(UserRegistrationDto registrationDto);
}
