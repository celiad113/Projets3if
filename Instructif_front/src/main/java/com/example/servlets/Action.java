package com.example.servlets;

import metiers.Service;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public abstract class Action {
    Service sc = new Service();
    public abstract void execute(HttpServletRequest request);
}
