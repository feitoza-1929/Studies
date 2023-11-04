using QueueService;

var builder = Host.CreateApplicationBuilder(args);
builder.Services.AddHostedService<QueuedHostedService>();
builder.Services.AddSingleton<MonitorLoop>();
builder.Services.AddSingleton<IBackgroundTaskQueue>(_ => 
{
    if (!int.TryParse(builder.Configuration["QueueCapacity"], out var queueCapacity))
        queueCapacity = 100;

    return new BackgroundTaskQueue(queueCapacity);
});

var host = builder.Build();

var monitorLoop = host.Services.GetRequiredService<MonitorLoop>();
monitorLoop.Run();

host.Run();
