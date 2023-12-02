using Microsoft.AspNetCore.Http.Features;
using Microsoft.EntityFrameworkCore;

public class ApplicationDbContext : DbContext
{
    public DbSet<Dog> Dogs { get; set; }
    public DbSet<Owner> Owners { get; set; }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        // modelBuilder.Entity<Dog>(builder =>
        //     builder.HasData(
        //         new Dog()
        //         {
        //             Id = Guid.Parse("467e18f2-b372-4f23-9105-d724e9922383"),
        //             Name = "Amora",
        //             Race = "NonSpecified",
        //             Age = 1,
        //             OwnerId = Guid.Parse("ee754e9b-f944-4b32-902e-a964848e985d")
        //         },
        //         new Dog()
        //         {
        //             Id = Guid.Parse("e74daceb-e731-42b9-a225-89c90c284775"),
        //             Name = "Lelouch",
        //             Race = "NonSpecified",
        //             Age = 5,
        //             OwnerId = Guid.Parse("2fbc3ec7-e69b-4fd8-85b1-09a8a4fe56fb")
        //         }
        //     )
        // );
        // modelBuilder.Entity<Owner>(builder =>
        //     builder.HasData(
        //         new Owner()
        //         {
        //             Id = Guid.Parse("ee754e9b-f944-4b32-902e-a964848e985d"),
        //             Name = "Jesse Faden"
        //         },
        //         new Owner()
        //         {
        //             Id = Guid.Parse("2fbc3ec7-e69b-4fd8-85b1-09a8a4fe56fb"),
        //             Name = "Tiago Feitoza"
        //         }
        //     ));
    }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseInMemoryDatabase("database");
    }
}