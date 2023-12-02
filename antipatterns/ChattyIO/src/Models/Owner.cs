public class Owner
{
    public Guid Id { get; set; }
    public string Name { get; set; }
    public ICollection<Dog> Dogs { get; }
}