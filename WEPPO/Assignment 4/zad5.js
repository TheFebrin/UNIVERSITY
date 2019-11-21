process.stdin.on('readable', () => {
    let name = process.stdin.read();
    process.stdout.write(`Hello ${name}`);
})