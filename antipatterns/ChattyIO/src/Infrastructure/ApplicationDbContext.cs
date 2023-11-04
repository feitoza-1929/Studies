using Microsoft.EntityFrameworkCore;

public class ApplicationDbContext : DbContext
{
    public DbSet<Dog> Dogs { get; set; }
    public DbSet<Owner> Owners { get; set; }

    public ApplicationDbContext(DbContextOptions options) : base(options)
    {
    }
}