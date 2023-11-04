public class Owner
{
    public Guid Id { get; set; }
    public string Name { get; set; }
    public virtual ICollection<Dog> Dogs { get; }
}