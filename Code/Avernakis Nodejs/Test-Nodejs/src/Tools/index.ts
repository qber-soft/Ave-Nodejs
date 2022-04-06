import * as path from "path";
import * as childProcess from "child_process";

export function devCompileResource(sourceDir: string, outDir: string) {
	//
	const ac = path.resolve(__dirname, "./lib/Avernakis-Compiler.exe");
	const mode = "-pg";
	const args = ["-id 00000010", "-idr 4", `-e *.svg`, `-ts ResId "${path.resolve(outDir, "./ResId.ts")}"`, `-t "${path.resolve(outDir, "./AppRes.txt")}"`, `-b "${path.resolve(outDir, "./AppRes.index")}"`, `-l "${path.resolve(outDir, "./AppRes.log")}"`, `"${sourceDir}"`].join(" ");

	//
	const command = `"${ac}" ${mode} ${args}`;
	console.log(command);
	childProcess.execSync(command);
}

// prod: production
export function prodCompileResource(sourceDir: string, outDir: string) {
	//
	const ac = path.resolve(__dirname, "./lib/Avernakis-Compiler.exe");
	const mode = "-p";
	const args = [`-o "${sourceDir}"`, `"${path.resolve(outDir, "./AppRes.index")}"`, `"${path.resolve(outDir, "./AppRes.bin")}"`].join(" ");

	//
	const command = `"${ac}" ${mode} ${args}`;
	console.log(command);
	childProcess.execSync(command);
}
