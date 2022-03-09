package com.example.task1;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.LinkedHashMap;


@RestController
@SpringBootApplication
public class Task1Application {

	Register registerService = new Register();

	public static void main(String[] args) {
		SpringApplication.run(Task1Application.class, args);
	}

	@GetMapping("/stats")
	public LinkedHashMap<String, Integer> stats(@RequestParam(value = "mode", defaultValue = StatsMode.TOP_THREE) String mode) {
		return registerService.getStats(mode);
	}

	@PostMapping("/register")
	public RegisterUserResponse register(@RequestParam(value = "name") String name) {
		registerService.registerUser(name);
		return new RegisterUserResponse("OK", registerService.getCountForUser(name));
	}

	@DeleteMapping("/delete")
	public void delete(@RequestParam(value = "name") String name) {
		registerService.deleteUser(name);
	}
}
