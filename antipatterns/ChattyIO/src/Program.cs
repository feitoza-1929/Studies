using System.Diagnostics;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddDbContext<ApplicationDbContext>();

using (var context = new ApplicationDbContext())
{
    context.Database.EnsureCreated();
    context.Dogs.AddRange(
        new Dog()
        {
            Id = Guid.Parse("467e18f2-b372-4f23-9105-d724e9922383"),
            Name = "Amora",
            Race = "NonSpecified",
            Age = 1,
            OwnerId = Guid.Parse("ee754e9b-f944-4b32-902e-a964848e985d")
        },
        new Dog()
        {
            Id = Guid.Parse("398065ca-7bb9-11ee-b962-0242ac120002"),
            Name = "Soia",
            Race = "NonSpecified",
            Age = 1,
            OwnerId = Guid.Parse("ee754e9b-f944-4b32-902e-a964848e985d")
        },
        new Dog()
        {
            Id = Guid.Parse("e74daceb-e731-42b9-a225-89c90c284775"),
            Name = "Lelouch",
            Race = "NonSpecified",
            Age = 5,
            OwnerId = Guid.Parse("2fbc3ec7-e69b-4fd8-85b1-09a8a4fe56fb")
        });

    context.Owners.AddRange(
        new Owner()
        {
            Id = Guid.Parse("ee754e9b-f944-4b32-902e-a964848e985d"),
            Name = "Jesse Faden"
        },
        new Owner()
        {
            Id = Guid.Parse("2fbc3ec7-e69b-4fd8-85b1-09a8a4fe56fb"),
            Name = "Tiago Feitoza"
        });
    context.SaveChanges();
}


var app = builder.Build();

//1.PROBLEM Multiple unnecessary HTTP Requests
app.MapGet("/dog/{id}/name", (Guid id, ApplicationDbContext db) => db.Dogs.Find(id)?.Name);
app.MapGet("/dog/{id}/race", (Guid id, ApplicationDbContext db) => db.Dogs.Find(id)?.Race);
app.MapGet("/dog/{id}/age", (Guid id, ApplicationDbContext db) => db.Dogs.Find(id)?.Age);
app.MapGet("/dog/{id}/owner", (Guid id, ApplicationDbContext db) => db.Dogs.Find(id)?.Owner);

//1.SOLUTION Just one request to get dog object entirely RIGHT
app.MapGet("/dog/{id}", (Guid id, ApplicationDbContext db) => db.Dogs.Find(id));

//2. PROBLEM Read and Write records to database as was different quer   ies
app.MapGet("/owner/dog/wrong", (ApplicationDbContext db) =>
{
    var owners = db.Owners;
    List<object> result = new();

    foreach (var owner in owners)
    {
        var dogs = db.Dogs
            .Where(x => x.OwnerId == owner.Id)
            .Select(x => new { x.Id, x.Name, x.OwnerId})
            .ToList();

        result.AddRange(dogs);
    }

    return result;
});

//2. SOLUTION Reduce the number of queries into a larger
app.MapGet("/owner/dog/right", (ApplicationDbContext db) =>
{
    return db.Owners
        .Join(db.Dogs, owner => owner, dog => dog.Owner, (owner, dog) => new { dog.Id, dog.Name, dog.OwnerId})
        .ToList();
});

app.Run();
