using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddDbContext<ApplicationDbContext>(
    options => options.UseInMemoryDatabase("teste")
);

var app = builder.Build();

app.MapGet("/", () => "Hello World!");

app.Run();
